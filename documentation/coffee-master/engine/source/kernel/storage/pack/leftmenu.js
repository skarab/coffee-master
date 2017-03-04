function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6335\" class=\"headerLeftMenuInActive\"><a id=\"aID6335\" href=\"#\" OnMouseOver=\"link('_dir','pack0',this)\" class=\"leftMenuLinkHeadInActive\">pack</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID835\" class=\"leftMenuInActive\"><a id=\"aID835\" href=\"#\" OnMouseOver=\"link('_class','Pack35340',this)\" class=\"leftMenuLinkInActive\">Pack</a></div>\n");
document.write("<div id=\"divID836\" class=\"leftMenuInActive\"><a id=\"aID836\" href=\"#\" OnMouseOver=\"link('_class','PackFile35340',this)\" class=\"leftMenuLinkInActive\">PackFile</a></div>\n");
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
