function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6344\" class=\"headerLeftMenuInActive\"><a id=\"aID6344\" href=\"#\" OnMouseOver=\"link('_dir','camera0',this)\" class=\"leftMenuLinkHeadInActive\">camera</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID845\" class=\"leftMenuInActive\"><a id=\"aID845\" href=\"#\" OnMouseOver=\"link('_class','Camera54809',this)\" class=\"leftMenuLinkInActive\">Camera</a></div>\n");
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
