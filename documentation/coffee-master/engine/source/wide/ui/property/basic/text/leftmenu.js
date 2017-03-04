function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6434\" class=\"headerLeftMenuInActive\"><a id=\"aID6434\" href=\"#\" OnMouseOver=\"link('_dir','text0',this)\" class=\"leftMenuLinkHeadInActive\">text</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID967\" class=\"leftMenuInActive\"><a id=\"aID967\" href=\"#\" OnMouseOver=\"link('_class','PropertyString49249',this)\" class=\"leftMenuLinkInActive\">PropertyString</a></div>\n");
document.write("<div id=\"divID968\" class=\"leftMenuInActive\"><a id=\"aID968\" href=\"#\" OnMouseOver=\"link('_class','PropertyText49249',this)\" class=\"leftMenuLinkInActive\">PropertyText</a></div>\n");
document.write("<div id=\"divID969\" class=\"leftMenuInActive\"><a id=\"aID969\" href=\"#\" OnMouseOver=\"link('_class','PropertyTextDialog49249',this)\" class=\"leftMenuLinkInActive\">PropertyTextDialog</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
