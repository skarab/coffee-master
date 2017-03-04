function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6382\" class=\"headerLeftMenuInActive\"><a id=\"aID6382\" href=\"#\" OnMouseOver=\"link('_dir','sky0',this)\" class=\"leftMenuLinkHeadInActive\">sky</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID892\" class=\"leftMenuInActive\"><a id=\"aID892\" href=\"#\" OnMouseOver=\"link('_class','Sky54809',this)\" class=\"leftMenuLinkInActive\">Sky</a></div>\n");
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
