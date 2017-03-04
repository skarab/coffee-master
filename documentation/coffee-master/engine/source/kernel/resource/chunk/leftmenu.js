function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6315\" class=\"headerLeftMenuInActive\"><a id=\"aID6315\" href=\"#\" OnMouseOver=\"link('_dir','chunk0',this)\" class=\"leftMenuLinkHeadInActive\">chunk</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID798\" class=\"leftMenuInActive\"><a id=\"aID798\" href=\"#\" OnMouseOver=\"link('_class','Chunk24579',this)\" class=\"leftMenuLinkInActive\">Chunk</a></div>\n");
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
